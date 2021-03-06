/**
 * @file NVRAM.hpp
 *
 * @date 27.01.2016
 * @author Andre
 * @description
 */
#ifndef NVRAM_HPP_
#define NVRAM_HPP_

#include "tools/Serializable.hpp"
#include "tools/TwoPointCalibration.hpp"
#include <stdint.h>

#define EBADCHECKSUM    1000

class NVRAM
{
public:
  NVRAM();
  virtual ~NVRAM() { };

  /** NVRAM memory layout
   *
   * Memory is divided into slots. Each slot additionally needs
   * 2 bytes for a CRC16 checksum.
   */
  enum MemoryLayout
  {
    CalibSetpointCurrent = 0x00, //!< CalibSetpointCurrent
    CalibActualVoltage   = 0x1A, //!< CalibActualVoltage
    CalibActualCurrent   = 0x34, //!< CalibActualCurrent

    MemorySize           = 0x4E  //!< Total size of memory layout
  };

  int clearMemorySlot(enum MemoryLayout memorySlot, unsigned int size);

  int loadMemorySlot(enum MemoryLayout memorySlot, Serializable& memoryData);

  int saveMemorySlot(enum MemoryLayout memorySlot, const Serializable& memoryData);

private:
  void lowLevelInit();

  void eraseParameters();

  int writeMemorySlot(enum MemoryLayout memorySlot, char* buf, unsigned int size);

  void writeParametersToFlash(uint32_t* parametersBuf, int size);
};

#endif /* NVRAM_HPP_ */
