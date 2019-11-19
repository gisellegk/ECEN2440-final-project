pwm_frequency = 100000;
pwm_period = pwm_frequency ^ -1;

sine_frequency = 600;
sine_period = sine_frequency ^ -1;

data_point_numbers = sine_period / pwm_period';

sampling_values = linspace(0, (2 * pi), data_point_numbers)';

discrete_sine_values = sin(sampling_values);

row_vector = (discrete_sine_values' + 1) * 50;

csvwrite("Row Vector.txt", row_vector)