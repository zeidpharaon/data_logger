s = serial('COM8');
set(s,'BaudRate',115200);
fopen(s);
pause(2) %

sec = -1;
while sec ~= 0
    c = clock;
    sec = c(6) - floor(c(6));
end

d = string(round(c));
ds =  d(1) + " " + d(2) + " " +d(3) + " " +d(4) + " " + d(5) + " " + d(6);
fprintf(s, "s " + ds);

fclose(s);
delete(s)
clear s