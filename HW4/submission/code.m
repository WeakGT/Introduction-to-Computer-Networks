% Load the adjacency matrix
load('network_A.mat'); % Assuming the matrix is stored in 'A' within network_A.mat

% load('input_test.mat');

% Number of nodes
n = size(A, 1);

% Initialize the distance matrix with inf
d = inf(n);

% Set the diagonal to zero (distance to self is zero)
for i = 1:n
    d(i, i) = 0;
end

% Set the distance for direct connections
for i = 1:n
    for j = 1:n
        if A(i, j) == 1
            d(i, j) = 1;
        end
    end
end

% Floyd-Warshall Algorithm
for k = 1:n
    for i = 1:n
        for j = 1:n
            if d(i, j) > d(i, k) + d(k, j)
                d(i, j) = d(i, k) + d(k, j);
            end
        end
    end
end

% Save the result
save('result.mat', 'd');