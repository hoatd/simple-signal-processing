#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <cmath>
#include <ctime>

int signum( double val ) {
    return int( double( 0 ) < val ) - int( val < double( 0 ) );
}

std::vector<double> sinusoid( double sampling_rate, double sampling_duration,
                             double frequency, double amplitude, double offset ) {
std::size_t sample_length = std::size_t( sampling_rate * sampling_duration );
    std::vector<double> samples;
    samples.reserve( sample_length );
    for( std::size_t sample_time_t = 0; sample_time_t < sample_length; ++sample_time_t ) {
        double sample_value = std::sin( sample_time_t * 2 * M_PI * frequency / sampling_rate + offset * M_PI / 180 );
        samples.push_back( amplitude * sample_value );
    }
    return samples;
}

std::vector<double> squarewave( double sampling_rate, double sampling_duration,
                               double frequency, double amplitude, double offset ) {
    std::size_t sample_length = std::size_t( sampling_rate * sampling_duration );
    std::vector<double> samples;
    samples.reserve( sample_length );
    for( std::size_t sample_time_t = 0; sample_time_t < sample_length; ++sample_time_t ) {
        double sample_value = signum( std::sin( sample_time_t * 2 * M_PI * frequency / sampling_rate + offset * M_PI / 180 ) );
        samples.push_back( amplitude * sample_value );
    }
    return samples;
}

int main() {
    std::srand( std::time( 0 ) ); // for adding noise

    double sine_frequency { 10 }; // Hz
    double sine_amplitude { 3 };
    double sine_offset { 90 }; // degrees
    double square_frequency { 40 }; // Hz
    double square_amplitude { 1 };
    double square_offset { 0 }; // degree
    double sampling_rate { 200 }; // Hz
    double sampling_duration { 1 }; // second
    std::vector<double> sine_signal = sinusoid( sampling_rate, sampling_duration,
                                               sine_frequency, sine_amplitude, sine_offset );
    std::vector<double> square_signal = squarewave( sampling_rate, sampling_duration,
                                                   square_frequency, square_amplitude, square_offset );

    // add some noises
    // double noise { 0.01 };
    // std::for_each( sine_signal.begin(), sine_signal.end(), [=]( double &value ){
    //                   value += value * noise * ( -1 + 2 * double( std::rand() ) / RAND_MAX ); } );
    // std::for_each( square_signal.begin(), square_signal.end(), [=]( double &value ){
    //                   value += value * noise * ( -1 + 2 * double( std::rand() ) / RAND_MAX ); } );

    std::vector<double> mixed_signal;
    mixed_signal.reserve( sine_signal.size() );
    std::transform( sine_signal.begin(), sine_signal.end(),
                    square_signal.begin(), std::back_inserter( mixed_signal ),
                    std::multiplies<double>() );

    unsigned int length_of_quarter = sampling_rate / 4;

    double mean_1st_quarter = std::accumulate( mixed_signal.begin(),
                                              mixed_signal.begin() + 1 * length_of_quarter, 0.0 ) / length_of_quarter;

    int N = 100;
    double integral_2nd_quarter = std::accumulate( mixed_signal.begin() + 1 * length_of_quarter,
                                                  mixed_signal.begin() + 2 * length_of_quarter, 0.0 ) * length_of_quarter / N;

    auto print = [](const auto vec) {
        size_t i;
        for ( i = 0; i < vec.size(); ++i ) {
            std::cout << std::fixed << std::setprecision(5) << vec[i] << " ";
            if ( ( i + 1 ) % 20 == 0 ) std::cout << std::endl;
        }
        if ( ( i + 1) % 20 == 0 ) std::cout << std::endl;
    };

    // Save to files
    // std::ofstream time_out( "time.txt" );
    // for ( size_t i = 0; i < sine_signal.size(); ++i ) time_out << i * 1 / sampling_rate << std::endl;
    // std::ofstream sine_out( "sine.txt" );
    // std::copy( sine_signal.begin(), sine_signal.end(), std::ostream_iterator<double> { sine_out, "\n" } );
    // std::ofstream square_out( "square.txt" );
    // std::copy( square_signal.begin(), square_signal.end(), std::ostream_iterator<double> { square_out, "\n" } );
    // std::ofstream mixed_out( "mixed.txt" );
    // std::copy( mixed_signal.begin(), mixed_signal.end(), std::ostream_iterator<double> { mixed_out, "\n" } );

    std::cout << "Sine wave (frequency=10Hz, amplitude=3, phase-offset=90°, sampling-frequency=200Hz in 1 second):" << std::endl;
    print( sine_signal );
    std::cout << "\nSymmetrical square wave (frequency=40Hz, amplitude=1, phase-offset=0°,, sampling-frequency=200Hz in 1 second):" << std::endl;
    print( square_signal );
    std::cout << "\nMixed signal by multiplying the sine wave and the symmetrical square wave:" << std::endl;
    print( mixed_signal );
    std::cout << "\nMean of the mixed signals first quarter: " << mean_1st_quarter << std::endl;
    std::cout << "\nApproximated integral of the mixed signals second quarter (N=" << N << "): " << integral_2nd_quarter << std::endl;

    return EXIT_SUCCESS;
}
