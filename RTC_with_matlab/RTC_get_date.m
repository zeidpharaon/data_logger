S = serial('COM8');
set(S,'BaudRate',115200);
fopen(S);
pause(2) %

sec_old = -1;
sec_new = -1;
while sec_new - sec_old ~= 1
    sec_old = sec_new;
    fprintf(S,'g');
    out = fscanf(S);
    splited_out = split(out);
    sec_new = str2double(splited_out{6});
end

y = str2double(splited_out{1}) + 2000;
mon = str2double(splited_out{2});
day = str2double(splited_out{3});
h = str2double(splited_out{4});
min = str2double(splited_out{5});
sec = str2double(splited_out{6});

t = datetime(y, mon, day, h, min, sec);
error = posixtime(t) - (posixtime(datetime(clock)))
fclose(S);
delete(S)
clear s