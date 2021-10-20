use serial::unix;
use rand::Rng;
use std::{
    thread,
    time,
    path::Path,
    io::{Write}
};
use anyhow::{Context, Result};

const LED_NUM: usize = 12;
const CHANNELS_NUM: usize = LED_NUM * 3;

fn main() -> Result<()> {

    let board_port = std::env::args()
        .nth(1)
        .with_context(|| format!("Failed to run app: no port was given"))?;

    if let Err(error) = set_fire(&board_port) {
        return Err(error.into())
    }

    Ok(())
}

fn set_fire(board_port: &str) -> Result<()> {
    let mut port = unix::TTYPort::open(Path::new(&board_port))?;

    let mut rgbs: Vec<u8> = vec![0; CHANNELS_NUM];
    let mut iteration: usize = 1;

    loop {
        for i in 0..iteration {
            rgbs[i] = rand::thread_rng().gen_range(0..255)
        }
        port.write(&rgbs[..iteration])?;
        iteration = (iteration + 1) % CHANNELS_NUM;

        thread::sleep(time::Duration::from_millis(100));
    }
}
