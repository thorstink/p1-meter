#include <array>
#include <asm/ioctls.h>
#include <asm/termbits.h>
#include <fcntl.h>
#include <stdio.h>     // printf
#include <sys/ioctl.h> // Used for TCGETS2, which is required for custom baud rates
#include <unistd.h>

int main() {
  const auto device_ = "/dev/ttyUSB0";
  // const auto baudRateType_ = BaudRateType::STANDARD;
  // const auto baudRateStandard_ = BaudRate::B_115200;
  // const auto numDataBits_ = NumDataBits::EIGHT;
  // const auto parity_ = Parity::NONE;
  // const auto numStopBits_ = NumStopBits::ONE;

  int fileDesc_ = open(device_, O_RDONLY);
  // Check status
  if (fileDesc_ == -1) {
    // THROW_EXCEPT("Could not open device \"" + device_ + "\". Is the device
    // name correct and do you have read/write permissions?");
  }

  struct termios2 tty;
  ioctl(fileDesc_, TCGETS2, &tty);
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_cflag |=
      CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_cflag &= ~CBAUD;
  tty.c_cflag |= CBAUDEX;
  tty.c_ispeed = 115200;
  tty.c_ospeed = 115200;

  tty.c_oflag = 0;       // No remapping, no delays
  tty.c_oflag &= ~OPOST; // Make raw

  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

  tty.c_lflag &=
      ~ICANON; // Turn off canonical input, which is suitable for pass-through
  // Configure echo depending on echo_ boolean
  tty.c_lflag &= ~ECHOE;  // Turn off echo erase (echo erase only relevant if
                          // canonical input is active)
  tty.c_lflag &= ~ECHONL; //
  tty.c_lflag &= ~ISIG;   // Disables recognition of INTR (interrupt), QUIT and
  // SUSP (suspend) characters
  //
  tty.c_cc[VTIME] = 0;
  tty.c_cc[VMIN] = 0;
  ioctl(fileDesc_, TCSETS2, &tty);

  // SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_115200,
  // NumDataBits::EIGHT,
  //                       Parity::NONE, NumStopBits::ONE);
  // serialPort.SetTimeout(2000); // Block for up to 100ms to receive data
  // serialPort.Open();

  constexpr size_t readBufferSize_B = 1024;
  std::array<char, readBufferSize_B> readBuffer_;
  int i = 0;
  ssize_t offset = 0;
  do {
    ssize_t n = read(fileDesc_, &readBuffer_[offset], readBufferSize_B);

    if (n <= 0) {
      // throw std::system_error(EFAULT, std::system_category());
    }
    offset += n;
    for (ssize_t i = 0; i < offset; i++) {
      printf("%c", readBuffer_[i]);
    }
  } while (i++ < 50);

  // serialPort.Close();
}
