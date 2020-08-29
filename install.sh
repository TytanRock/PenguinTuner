curl -s --compressed "https://penguintuner.tytan.rocks/KEY.gpg" | sudo apt-key add -
sudo curl -s --compressed -o /etc/apt/sources.list.d/penguintuner.list "https://penguintuner.tytan.rocks/penguintuner.list"
sudo apt update

