use std::{
    env,
    error::Error,
    io::{Write, stdin, stdout},
    path::PathBuf,
    process::{Child, Command, Stdio},
};

fn main() -> Result<(), Box<dyn Error>> {
    loop {
        print!("> ");
        stdout().flush()?;

        let mut input = String::new();
        stdin().read_line(&mut input)?;
        let input = input.trim();

        if input.is_empty() {
            continue;
        }

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
                    }
                }
                "exit" => {
                    println!("Goodbye!");
                    return Ok(());
                }
                command => {
                    let stdin = match prev_stdout.take() {
                        Some(output) => { Stdio::from(output) }
                        None => { Stdio::inherit() }
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
}
