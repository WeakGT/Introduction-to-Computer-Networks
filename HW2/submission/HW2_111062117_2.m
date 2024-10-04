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
E = zeros(1, 12032);
for i=2:12029
    for j=i+1:12030
        for k=j+1:12031
            for l=k+1:12032
                E = zeros(1, 12032);
                E([i, j, k, l]) = 1;
                for x=1:12000
                    if E(i) ~= 0
                        RR = xor(E(i + 1:i + 32), C(2:33));
                        E(i + 1:i + 32) = RR;
                    end
                end
                if sum(RR) == 0
                   E = zeros(1, 12032);
                   E([i, j, k, l]) = 1;
                   error = E;
                   save("111062117.mat", "codepacket", "error");
                   return;
                end
            end
        end
    end
end
