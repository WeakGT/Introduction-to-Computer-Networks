load("inputdata")
C = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
T = [packet, zeros(1, 32)];
for i=1:12000
    if T(i) ~= 0
        R = xor(T(i + 1:i + 32), C(2:33));
        T(i + 1:i + 32) = R;
    end
end
codepacket = [packet, T(12001:12032)];