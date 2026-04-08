use std::{
    env,
    error::Error,
    io::{Write, stdin, stdout},
    path::PathBuf,
    process::Command,
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

        let mut parts = input.split_whitespace();
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
                let mut cmd = Command::new(command);
                cmd.args(&args);

                match cmd.spawn() {
                    Ok(mut child) => match child.wait() {
                        Ok(status) => {
                            if !status.success() {
                                eprintln!(
                                    "Command '{}' failed with exit code: {:?}",
                                    command,
                                    status.code()
                                );
                            }
                        }
                        Err(err) => {
                            eprintln!("Failed to wait for command '{}': {}", command, err);
                        }
                    },
                    Err(err) => {
                        eprintln!("Failed to execute command '{}': {}", command, err);
                    }
                }
            }
        }
    }
}
