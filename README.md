# Minutify - meeting minutes generator

<p align="center">
<img src="https://raw.githubusercontent.com/s1ddh3sh/minutify/main/docs/assets/minutify-logo.png" width="450">
</p>

**Minutify** is a _personal AI meeting minutes generator_ you can run with the help of a <a href="https://core.telegram.org/bots" target="_blank">Telegram Bot</a>. The bot accepts the audio recording file (currently) from the user bot and with the help of LLM it can generate the transcription as well as a list of TODOs in a well-documented format.

## Project Achitecture

<p align="center">
<img src="https://raw.githubusercontent.com/s1ddh3sh/minutify/main/docs/assets/minutify.png" width="630" alt="Project Architecture">
</p>

## Project Status (current)

- [x] Initial Bot setup
- [ ] Audio file processing
- [ ] LLM (local/ cloud) config
- [ ] Transcription and Summary
- [ ] Deployment

## Build from source (development)

Required for tg-bot (Refer <a href="https://github.com/reo7sp/tgbot-cpp" target="_blank">tgbot-cpp</a> for more)

```bash
sudo apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev #refer tgbot-cpp

git clone --recursive https://github.com/s1ddh3sh/minutify.git
cd minutify
```

Create your telegram bot using <a href="https://telegram.me/BotFather" target="_blank">telegram.me/BotFather</a>
<br>Export your `BOT_TOKEN` :

```bash
export BOT_TOKEN=<YOUR_TOKEN>
```

Make and run

```bash
mkdir build && cd build
cmake .. && make
./minutify
```
