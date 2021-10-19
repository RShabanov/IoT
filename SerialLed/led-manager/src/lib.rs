mod mqtt;
use mqtt::MqttSubscriber;
use paho_mqtt::errors::Result;
use serial::unix;
use std::{
    path::Path,
    io::Write,
    time::Duration
};
use serial::core::prelude::*;

const DFLT_BROKER: &str = "broker.hivemq.com";
const DFLT_CLIENT: &str = "shr-subscriber";
const TOPIC: &str = "light/lights-shr";
// const DEFAULT_PORT: &str = "/dev/ttyUSB0";

pub fn set_fire(board_port: &str) -> Result<()> {
    let mut port = unix::TTYPort::open(Path::new(&board_port))
        .unwrap();

    // port.set_timeout(Duration::from_millis(1000)).unwrap();

    let mut subscriber = MqttSubscriber::new(DFLT_BROKER, DFLT_CLIENT)?;
    subscriber.connect(60)?;

    let rx = subscriber.consume();
    subscriber.client.subscribe(TOPIC, 2)?;

    for msg in rx.iter() {
        if let Some(msg) = msg {

            let rgb: Vec<u8> =
                msg.payload_str()
                .trim_matches(|c| c == '[' || c == ']')
                .split(',')
                .map(|n| n.trim().parse().unwrap())
                .collect();

            port.write(&rgb[..])?;
        }
    }

    subscriber.disconnect()?;

    Ok(())
}