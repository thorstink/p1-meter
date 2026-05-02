#include <CppLinuxSerial/SerialPort.hpp>
#include <array>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

using namespace mn::CppLinuxSerial;

int main() {
  SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT,
                        Parity::NONE, NumStopBits::ONE);
  serialPort.SetTimeout(2000); // Block for up to 100ms to receive data
  serialPort.Open();

  std::array<char, 255> readBuffer_;
  unsigned char readBufferSize_B;
  ssize_t n = read(serialPort.fileDesc_, &readBuffer_[0], readBufferSize_B);

  int i = 0;
  do {

    if (n <= 0) {
      // Read was unsuccessful
      throw std::system_error(EFAULT, std::system_category());
    }
    for (ssize_t i = 0; i < n; i++) {
      printf("%c", readBuffer_[i]);
    }
  } while (i++ < 10);

  serialPort.Close();
}
