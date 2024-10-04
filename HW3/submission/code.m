% Load the adjacency matrix of the network from file
load('network_A.mat');

% Determine the number of nodes in the network
n = size(A, 1);  

% Initialize arrays to store level and parent information
level = zeros(n); % Array to store the level of each node
parent = zeros(n); % Array to store the parent of each node

% Set the root node's level to 1
level(1) = 1; 

% Traverse the network to assign levels and parents to each node
for L = 2:n
    for i = 1:n
        % Check if the current node's level is L - 1
        if level(i) == L - 1
            % Traverse neighbors of node i
            for j = 1:n
                % If node j is a neighbor of node i and its parent is not assigned
                if A(i, j) == 1 && parent(j) == 0
                    level(j) = L; % Assign level L to node j
                    parent(j) = i; % Record node i as the parent of node j
                end
            end
        end
    end
end

% Initialize array to represent the resulting tree structure
tree = zeros(n);

% Populate the tree array based on parent-child relationships
for i = 1:n
    tree(i, parent(i)) = 1; % Set the edge from parent to child
    tree(parent(i), i) = 1; % Set the edge from child to parent
end

% Save the resulting tree structure to a file
save('result.mat','tree');
