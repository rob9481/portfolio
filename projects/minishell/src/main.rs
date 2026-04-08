use std::{
    env,
    error::Error,
    fs,
    path::PathBuf,
    process::{Child, Command, Stdio},
};

use rustyline::{DefaultEditor, error::ReadlineError};

fn generate_prompt() -> String {
    if let Ok(pathbuf) = env::current_dir()
        && let Some(s) = pathbuf.to_str()
    {
        let mut s = String::from(s);
        s.push_str("> ");
        return s;
    }
    String::from("> ")
}

fn handle_cd(args: &Vec<&str>, prompt: &mut String) {
    let new_dir = args.first().unwrap_or(&"/");

    // redirect ~ to user's HOME
    let mut root = PathBuf::new();
    if new_dir.starts_with('~')
        && let Some(home_dir) = dirs::home_dir()
    {
        root.push(home_dir);
        root.push(new_dir[1..].trim_start_matches('/'));
    } else {
        root.push(new_dir);
    }

    if let Err(err) = env::set_current_dir(&root) {
        eprintln!("cd: {}", err);
    } else {
        prompt.clear();
        prompt.push_str(&generate_prompt());
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut prompt = generate_prompt();
    let mut rl = DefaultEditor::new()?;
    let history = "/tmp/.minishell_history";
    match rl.load_history(history) {
        Ok(_) => {}
        Err(ReadlineError::Io(_)) => {
            fs::File::create(history)?;
        }
        Err(err) => {
            eprintln!("minishell: Error loading history: {}", err);
        }
    }

    'outer: loop {
        match rl.readline(&prompt) {
            Ok(line) => {
                let input = line.trim();

                if input.is_empty() {
                    continue;
                }
                rl.add_history_entry(input)?;

                let mut commands = input.trim().split(" | ").peekable();
                let mut prev_stdout = None;
                let mut children: Vec<Child> = Vec::new();

                while let Some(command) = commands.next() {
                    let mut parts = command.split_whitespace();
                    let Some(command) = parts.next() else {
                        continue;
                    };
                    let args: Vec<&str> = parts.collect();

                    match command {
                        "cd" => {
                            handle_cd(&args, &mut prompt);
                        }
                        "exit" => {
                            println!("Goodbye!");
                            break 'outer;
                        }
                        command => {
                            let stdin = match prev_stdout.take() {
                                Some(output) => Stdio::from(output),
                                None => Stdio::inherit(),
                            };

                            let stdout = if commands.peek().is_some() {
                                Stdio::piped()
                            } else {
                                Stdio::inherit()
                            };

                            let child = Command::new(command)
                                .args(args)
                                .stdin(stdin)
                                .stdout(stdout)
                                .spawn();

                            match child {
                                Ok(mut child) => {
                                    prev_stdout = child.stdout.take();
                                    children.push(child);
                                }
                                Err(err) => {
                                    eprintln!("Failed to execute '{}': {}", command, err);
                                    break;
                                }
                            }
                        }
                    }
                }

                for mut child in children {
                    let _ = child.wait();
                }
            }
            Err(ReadlineError::Interrupted) | Err(ReadlineError::Eof) => {
                println!("\nExiting minishell");
                break;
            }
            Err(err) => {
                eprintln!("minishell: Error: {:?}", err);
            }
        }
    }

    rl.save_history(history)?;
    Ok(())
}
