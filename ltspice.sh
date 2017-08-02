#Taken from https://gist.github.com/daniw/7439488

# install wine and ltspice
sudo apt-get install wine
# sudo pacman -S wine
cd /tmp/
wget http://ltspice.linear-tech.com/software/LTspiceIV.exe
wine LTspiceIV.exe
rm LTspiceIV.exe

# start lstpice through wine
wine ~/.wine/drive_c/Program\ Files/LTC/LTspiceIV/scad3.exe

# start ltspice through wine with /tmp/example.asc
wine ~/.wine/drive_c/Program\ Files/LTC/LTspiceIV/scad3.exe /tmp/example.asc

