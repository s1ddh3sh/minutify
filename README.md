# Minutify - meeting minutes generator

<p align="center">
<img src="https://raw.githubusercontent.com/s1ddh3sh/minutify/main/docs/assets/minutify-logo.png" width="450">
</p>

**Minutify** is a _personal AI meeting minutes generator_ you can run with the help of a [Telegram Bot](https://core.telegram.org/bots). It accepts the audio recording file (currently) from the user and can generate the transcription as well as a list of TODOs in a well-documented format.

## Project Achitecture

<p align="center">
<img src="https://raw.githubusercontent.com/s1ddh3sh/minutify/main/docs/assets/minutify.png" width="630" alt="Project Architecture">
</p>

## Project Status (current)

- [x] Initial Bot setup
- [ ] Audio file processing
- [ ] Transcription and Summary
- [ ] Deployment

## Build from source (development)

Required for tg-bot (Refer [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) for more)

```bash
sudo apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev #refer tgbot-cpp

git clone --recursive https://github.com/s1ddh3sh/minutify.git
cd minutify
```

Export your telegram `BOT_TOKEN` :

```bash
export BOT_TOKEN=<YOUR_TOKEN>
```

Make and run

```bash
mkdir build && cd build
cmake .. && make
./minutify
```
