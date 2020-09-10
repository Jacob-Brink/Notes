start cmd.exe /k "FOR /L %%N IN () DO plink.exe -v -ssh -batch -C -T -N -L 22000:127.0.0.1:22012 jacob@172.105.23.21 -P 22 -i C:\Users\jacob\Documents\Putty\Keys\linodePrivateKey.ppk <NUL"
