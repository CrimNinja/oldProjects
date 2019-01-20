%% Generate the data points

n_points = 4;
total_distance = 5; % in m

X = linspace(0, total_distance, n_points)';
% y = linspace(0, total_distance, n_points)';
Y = zeros(n_points, 1); % to have one dimension

true_coordinates = round([X, Y], 4);

%% Set known points

% known_FPs = 1:2:n_points;
known_FPs = [2, n_points];
number_known_FPs = numel(known_FPs);

%% Compute distance and select neighbors

% Distance between points is the same, lets add some noise to it to
% simulate an approximate distance estimate if needed.

dist = squareform(pdist(true_coordinates));

distance_threshold = 0.4 * max(dist(:));

neighbours = find(dist < distance_threshold);

%% this is a test section

% neighbours = diag(diag(dist, 1), 1) + diag(diag(dist, 2), 2);
% neighbours = find(neighbours + neighbours.');

%%

dist(eye(size(dist)) == 1) = inf;

% Document code well !!! %
[I, J] = ind2sub(size(dist), neighbours);
selected_indices = I > J;
I = I(selected_indices);
J = J(selected_indices);

%%

A1 = zeros(2 * n_points, 2 * n_points);
b1 = zeros(2 * n_points, 1);
b2 = dist(sub2ind(size(dist), I, J));

for ii = 1:number_known_FPs
    A1((2 * ii) - 1, 2 * known_FPs(ii) - 1) = 1;
    b1((2 * ii) - 1, 1) = true_coordinates(known_FPs(ii), 1);
    A1((2 * ii), 2 * known_FPs(ii)) = 1;
    b1((2 * ii), 1) = true_coordinates(known_FPs(ii), 2);
end

A2 = zeros(2 * numel(I), 2 * n_points);
%x-coordinate
A2(sub2ind(size(A2), (1:numel(I))', (2 * I(:)) - 1)) = 1;
A2(sub2ind(size(A2), (1:numel(I))', (2 * J(:)) - 1)) = -1;

%y-coordinate
A2(sub2ind(size(A2), (numel(I) + (1:numel(I)))', 2 * I(:))) = 1;
A2(sub2ind(size(A2), (numel(I) + (1:numel(I)))', 2 * J(:))) = -1;

%% Model and estimation

testFunction = @(x, A1, b1, A2, b2) [b1 - A1 * x; b2 - sqrt([eye(size(A2, 1) / 2), eye(size(A2, 1) / 2)] * ((A2 * x).^2))];

options = optimoptions('lsqnonlin');
estimated_coordinates = lsqnonlin(@(x) testFunction(x, A1, b1, A2, b2), zeros(size(A1, 2), 1), [], [], options);
estimated_coordinates = round(estimated_coordinates, 4);

%% Calculate errors

error = sqrt((true_coordinates(1:end, 1) - estimated_coordinates(1:2:end)).^2 + (true_coordinates(1:end, 2) - estimated_coordinates(2:2:end)).^2);
meanError = mean(error);
deviation = std(error);
variance = var(error);


%% Plot verification

figure
plot(X, Y, 'ro')
hold on
% plot(true_coordinates([1, end], 1), true_coordinates([1, end], 2))
plot(estimated_coordinates(1:2:end), estimated_coordinates(2:2:end), 'b*')
plot([true_coordinates(1:end, 1), estimated_coordinates(1:2:end)]', [true_coordinates(1:end, 2), estimated_coordinates(2:2:end)]', 'k-')
grid on, grid minor
title(['Mean error: ', num2str(meanError), ', Variance: ', num2str(variance), '.'])
% annotation('textbox', [0.2, 0.5, 0.3, 0.3], 'String', ['Mean error: ', num2str(meanError), ', Variance: ', num2str(variance), '.'], ...
%     'FitBoxToText', 'on')
hold off


%% add weights and repeat

Weights = inv(diag([ones(numel(b1), 1); 100 * b2 + 10]));

weightFunction = @(x, A1, b1, A2, b2, Weights) Weights * [b1 - A1 * x; b2 - sqrt([eye(size(A2, 1) / 2), eye(size(A2, 1) / 2)] * ((A2 * x).^2))];

options = optimoptions('lsqnonlin');
estimated_coordinates_w = lsqnonlin(@(x) weightFunction(x, A1, b1, A2, b2, Weights), zeros(size(A1, 2), 1), [], [], options);
estimated_coordinates_w = round(estimated_coordinates_w, 4);

%% calculate errors for weighted tasks

error_w = sqrt((true_coordinates(1:end, 1) - estimated_coordinates_w(1:2:end)).^2 + (true_coordinates(1:end, 2) - estimated_coordinates_w(2:2:end)).^2);
meanError_w = mean(error_w);
deviation_w = std(error_w);
variance_w = var(error_w);


%% Plot verification for weighted tasks

figure
plot(X, Y, 'ro')
hold on
% plot(true_coordinates([1, end], 1), true_coordinates([1, end], 2))
plot(estimated_coordinates_w(1:2:end), estimated_coordinates_w(2:2:end), 'b*')
plot([true_coordinates(1:end, 1), estimated_coordinates_w(1:2:end)]', [true_coordinates(1:end, 2), estimated_coordinates_w(2:2:end)]', 'k-')
grid on, grid minor
title(['Mean error: ', num2str(meanError), ', Variance: ', num2str(variance), '.'])
hold off




