#include <CppLinuxSerial/SerialPort.hpp>

using namespace mn::CppLinuxSerial;

int main() {
	SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	serialPort.SetTimeout(2000); // Block for up to 100ms to receive data
	serialPort.Open();
	std::string readData;
	serialPort.Read(readData);
	std::cout << "Read data = \"" << readData << "\"" << std::endl;

	serialPort.Close();
}
