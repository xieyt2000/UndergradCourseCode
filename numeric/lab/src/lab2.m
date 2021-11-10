x = 0:0.1:40;
y = besselj(0, x);
plot(x,y);
grid on;
hold on;
xlabel('x');
ylabel('y');
cnt = 1;
a = -1;
ans = zeros(10, 1);
while cnt <= 10
    a = a + 1;
    try
        z = fzerotx(@ (x) besselj(0, x), [a,a + 1]);
    catch
        continue;
    end
    ans(cnt) = z;
    cnt = cnt + 1;
    plot(z, 0, 'o');
end
ans