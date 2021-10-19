use paho_mqtt::errors::Result;
use led_manager::set_fire;

fn main() -> Result<()> {

    let board_port = std::env::args()
        .nth(1)
        .expect("no port given");

    set_fire(&board_port)
}


