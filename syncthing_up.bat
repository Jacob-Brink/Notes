start cmd.exe /k "FOR /L %%N IN () DO plink.exe -v -ssh -batch -C -T -N -R 8384:127.0.0.1:12345 jacob@172.105.23.21 -P 22 -i C:\Users\jacob\Documents\Putty\Keys\linodePrivateKey.ppk <NUL"
