use paho_mqtt::create_options::*;
use paho_mqtt::connect_options::*;
use paho_mqtt::server_response::ServerResponse;
use paho_mqtt::errors::Result;
use std::time::Duration;

pub struct MqttPubliser {
    pub client: paho_mqtt::Client,
    pub broker: String,
}

impl MqttPubliser {
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

    pub fn publish(
        &self,
        topic: &str,
        msg: &str,
        qos: i32
    ) -> Result<()> {
        if qos > 3 {
            return Err(paho_mqtt::errors::BadQos);
        }

        let msg = paho_mqtt::Message::new(topic, msg, qos);
        
        self.client.publish(msg)
    }

    pub fn disconnect(self) -> Result<()> {
        self.client.disconnect(None)?;
        Ok(())
    }
}
