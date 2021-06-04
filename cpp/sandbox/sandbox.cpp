#include <iostream>
#include <vector>

double avg(std::vector<double> vec) {
  double sum = 0;

  for (double ratio : vec) {
    sum += ratio;
  }

  return sum / vec.size();
}

int main() {
  double aapl = avg({
      (0.27 / 0.74),
      (0.10 / 1.22),
      (0.00 / 0.64),
      (0.10 / 0.58),
      (0.13 / 0.39),
      (0.17 / 0.59),
      (0.20 / 0.48),
      (0.17 / 0.47),
      (0.23 / 0.68),
      (0.13 / 0.87),
      (0.04 / 0.45),
      (0.11 / 0.43),
      (0.12 / 0.27),
      (0.17 / 0.37),
      (0.06 / 0.53),
      (0.19 / 0.49),
      (0.15 / 0.52),
  });

  double amd = avg({
      (0.08 / 0.43),
      (0.12 / 0.84),
      (0.23 / 0.95),
      (0.14 / 0.49),
      (0.11 / 0.44),
      (0.16 / 0.37),
      (0.06 / 0.34),
      (0.12 / 0.24),
      (0.01 / 0.48),
      (0.09 / 0.42),
      (0.11 / 0.28),
      (0.14 / 0.31),
  });

  double ba = avg({
      (0.78 / 1.62), (0.23 / 0.66), (0.05 / 0.92), (0.29 / 0.96), (0.07 / 0.96),
      (0.31 / 0.96), (0.69 / 1.06), (0.04 / 1.06), (0.16 / 1.06), (0.07 / 1.00),
      (0.19 / 0.91), (0.20 / 0.55), (0.00 / 0.66), (0.10 / 0.66), (0.24 / 0.66),
      (0.21 / 0.69), (0.31 / 0.82), (0.02 / 0.17), (0.18 / 0.22), (0.01 / 0.35),
      (0.20 / 0.35), (0.15 / 0.47), (0.33 / 0.57), (0.31 / 0.87), (0.37 / 1.12),
  });

  double fb = avg({
      (0.81 / 2.26), (0.95 / 2.90), (0.49 / 3.79), (0.51 / 1.50), (0.92 / 1.45),
      (1.86 / 2.26), (0.26 / 4.05), (0.40 / 1.00), (0.53 / 1.42), (0.63 / 1.93),
      (1.22 / 1.56), (0.13 / 1.52), (0.11 / 1.52), (0.04 / 1.14), (0.16 / 0.80),
      (0.24 / 0.60), (0.01 / 0.71), (0.12 / 0.71), (0.09 / 0.72), (0.06 / 0.72),
  });

  double msft = avg({
      (0.51 / 1.42),
      (0.36 / 2.34),
      (0.25 / 1.10),
      (0.34 / 1.10),
      (0.25 / 1.20),
      (0.21 / 0.71),
      (0.10 / 0.60),
      (0.12 / 0.36),
      (0.20 / 0.55),
      (0.17 / 0.75),
      (0.04 / 0.44),
      (0.20 / 0.50),
      (0.00 / 0.70),
  });

  double snap = avg({
      (0.36 / 0.73), (0.12 / 1.06), (0.38 / 1.06), (0.34 / 1.11), (0.29 / 1.11),
      (0.25 / 0.91), (0.19 / 0.82), (0.01 / 0.65), (0.11 / 0.31), (0.00 / 0.30),
      (0.11 / 0.30), (0.15 / 0.31), (0.16 / 0.43), (0.16 / 0.51), (0.11 / 0.32),
      (0.11 / 0.42), (0.08 / 0.52), (0.00 / 0.18), (0.06 / 0.16), (0.11 / 0.19),
      (0.16 / 0.32),
  });

  double tsla = avg({
      (5.35 / 10.83),
      (3.88 / 16.18),
      (1.11 / 8.00),
      (0.69 / 5.15),
      (1.07 / 4.52),
      (1.27 / 2.61),
      (1.38 / 3.69),
      (2.24 / 5.18),
      (1.14 / 6.90),
      (0.43 / 3.77),
      (0.82 / 4.20),
      (0.04 / 3.50),
      (0.89 / 3.10),
  });

  std::cout << "AAPL: " << aapl << std::endl;
  std::cout << "AMD: " << amd << std::endl;
  std::cout << "BA: " << ba << std::endl;
  std::cout << "FB: " << fb << std::endl;
  std::cout << "MSFT: " << msft << std::endl;
  std::cout << "SNAP: " << snap << std::endl;
  std::cout << "TSLA: " << tsla << std::endl;

  std::cout << "Overall Average: "
            << avg({
                   aapl,
                   amd,
                   ba,
                   fb,
                   msft,
                   snap,
                   tsla,
               })
            << std::endl;
}
