# echo docker run -it --mount type=bind,source="${PWD}"/../../firmware,target=/home --mount src="${PWD}"/../../output,target=/mnt,type=bind  jpconstantineau/arduino-cli-bluefruit-nrf52 /arduino-cli compile -v --fqbn adafruit:nrf52:feather52832 /home/firmware.ino  -o /mnt/output
# docker run -it  --mount src="${PWD}"/../..,target=/mnt,type=bind jpconstantineau/uf2conv:latest /bin/bash /mnt/build/docker/nrf52840uf2.sh all:all:all

# docker run -v /var/run/docker.sock:/var/run/docker.sock  --mount src="${PWD}"/../..,target=/mnt,type=bind -ti docker
docker run -it  --mount src="${PWD}"/../..,target=/mnt,type=bind jpconstantineau/arduino-cli-bluefruit-nrf52:latest /bin/bash 
