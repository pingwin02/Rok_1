#!/bin/bash

# If snap store is corrupted
# snap-store --quit
# sudo snap remove snap-store
# sudo snap install snap-store


gnome-terminal -- bash -c "
sudo apt upgrade
sudo apt autoremove
sudo apt upgrade
sudo snap refresh
exec bash"
