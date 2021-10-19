use paho_mqtt::create_options::*;
use paho_mqtt::connect_options::*;
use paho_mqtt::server_response::ServerResponse;
use paho_mqtt::errors::Result;
use paho_mqtt::Message;
use std::sync::mpsc::Receiver;
use std::time::Duration;

pub struct MqttSubscriber {
    pub client: paho_mqtt::Client,
    pub broker: String,
}

impl MqttSubscriber {
    pub fn new(host: &str, client: &str) -> Result<Self> {

        let create_opts = CreateOptionsBuilder::new()
            .server_uri(host)
            .client_id(client.to_string())
            .finalize();

        let client = paho_mqtt::Client::new(create_opts)?;

        Ok(Self {
            client,
            broker: host.to_string(),
        })
    }

    pub fn connect(&self, alive_interval: u64) -> Result<ServerResponse> {
        let connect_options = paho_mqtt::ConnectOptionsBuilder::new()
            .keep_alive_interval(Duration::from_secs(alive_interval))
            .clean_session(true)
            .finalize();

        self.client.connect(connect_options)
    }

    pub fn consume(&mut self) -> Receiver<Option<Message>> {
        self.client.start_consuming()
    }

    pub fn disconnect(self) -> Result<()> {
        self.client.disconnect(None)?;
        Ok(())
    }
}
