#include "async_queue.hpp"
#include "parallel.hpp"
#include <chrono>

using namespace std::chrono;

using namespace std;

int main(int argc, char *argv[])
{
  auto iter = dim_t{{size_t(20000000 * argc), size_t(1000), size_t(1), size_t(16)}};

  auto vec_size = get<0>(iter) * get<2>(iter) * get<2>(iter) * get<3>(iter);
  vector<float> out(vec_size);
  vector<float> in(vec_size);
  {
    auto start = high_resolution_clock::now();
    for(size_t i = 0; i < get<3>(iter); i++) {
      for(size_t j = 0; j < get<2>(iter); j++) {
        for(size_t k = 0; k < get<1>(iter); k++) {
          for(size_t l = 0; l < get<0>(iter); l++) {
            out[i*get<3>(iter) + j * get<2>(iter) + k *get<1>(iter) + l ] = (in[i*get<3>(iter) + j * get<2>(iter) + k *get<1>(iter) + l ] );
          }
        }
      }
    }
    size_t ms = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    std::cout << "duration: " << ms << "ms"<< std::endl;
    std::cout << out[24] << endl;
  }

  {
    auto start = high_resolution_clock::now();
    parallel_mat par(iter, [&](const dim_t &loc) {
        out[get<3>(loc) * get<3>(iter) + get<2>(loc) * get<2>(iter) + get<1>(loc) * get<1>(iter) + loc[0]] =
          (in[get<3>(loc) * get<3>(iter) + get<2>(loc) * get<2>(iter) + get<1>(loc) * get<1>(iter) + loc[0]]);
      });

    auto ms = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    std::cout << "duration: " << ms << "ms"<< std::endl;
    std::cout << out[24] << endl;
  }

  return 0;
}


