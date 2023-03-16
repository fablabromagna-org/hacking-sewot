# WebThings

WebThings demo.

Once the upload to the board is completed, connect to the same WiFi network and run the following commands.

Get the device WoT description (usage of `jq` for JSON pretty and colored printing):

```bash
curl http://192.168.104.65/things/led | jq
```

Change the property of the web astraction of the device, the paylaod should be:
- `0` to turn off the LED
- `1` to turn on the LED

```bash
curl \
    -H "Content-Type: application/json" \
    -H "Accept: application/json" \
    -X PUT -d '{"on":0}' \
    --insecure \
    http://192.168.104.65/things/led/properties/on
```
