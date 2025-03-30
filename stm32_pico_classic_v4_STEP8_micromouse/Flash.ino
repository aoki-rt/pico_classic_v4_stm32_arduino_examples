// Copyright 2025 RT Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

void mapWrite(void) {
  unsigned int m = 0;
  uint64_t data;

  flashErase(MAP_PAGE);

  HAL_FLASH_Unlock();

  for (int n = 0; n < MAZESIZE_X; n++) {
    for (int j = 0; j < (MAZESIZE_Y / 8); j++) {
      data = ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(7 + j * 8)) << 56)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(6 + j * 8)) << 48)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(5 + j * 8)) << 40)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(4 + j * 8)) << 32)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(3 + j * 8)) << 24)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(2 + j * 8)) << 16)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(1 + j * 8)) << 8)
             | ((uint64_t)g_map.wallDataRawGet((unsigned char)n, (unsigned char)(0 + j * 8)));

      flashPalamWrite(MAP_ADD + m, data);
      m = m + 8;
    }
  }
  HAL_FLASH_Lock();
}

void mapCopy(void) {
  unsigned int m = 0;
  uint64_t data;

  for (int n = 0; n < MAZESIZE_X; n++) {
    for (int j = 0; j < (MAZESIZE_Y / 8); j++) {
      data = flashPalamRead(MAP_ADD + m);
      g_map.wallDataSet((unsigned char)n, (unsigned char)(0 + j * 8), north, (unsigned char)(data & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(0 + j * 8), east, (unsigned char)((data >> 2) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(0 + j * 8), south, (unsigned char)((data >> 4) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(0 + j * 8), west, (unsigned char)((data >> 6) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(1 + j * 8), north, (unsigned char)((data >> 8) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(1 + j * 8), east, (unsigned char)((data >> 10) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(1 + j * 8), south, (unsigned char)((data >> 12) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(1 + j * 8), west, (unsigned char)((data >> 14) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(2 + j * 8), north, (unsigned char)((data >> 16) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(2 + j * 8), east, (unsigned char)((data >> 18) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(2 + j * 8), south, (unsigned char)((data >> 20) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(2 + j * 8), west, (unsigned char)((data >> 22) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(3 + j * 8), north, (unsigned char)((data >> 24) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(3 + j * 8), east, (unsigned char)((data >> 26) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(3 + j * 8), south, (unsigned char)((data >> 28) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(3 + j * 8), west, (unsigned char)((data >> 30) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(4 + j * 8), north, (unsigned char)((data >> 32) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(4 + j * 8), east, (unsigned char)((data >> 34) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(4 + j * 8), south, (unsigned char)((data >> 36) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(4 + j * 8), west, (unsigned char)((data >> 38) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(5 + j * 8), north, (unsigned char)((data >> 40) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(5 + j * 8), east, (unsigned char)((data >> 42) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(5 + j * 8), south, (unsigned char)((data >> 44) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(5 + j * 8), west, (unsigned char)((data >> 46) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(6 + j * 8), north, (unsigned char)((data >> 48) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(6 + j * 8), east, (unsigned char)((data >> 50) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(6 + j * 8), south, (unsigned char)((data >> 52) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(6 + j * 8), west, (unsigned char)((data >> 54) & 0x03));

      g_map.wallDataSet((unsigned char)n, (unsigned char)(7 + j * 8), north, (unsigned char)((data >> 56) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(7 + j * 8), east, (unsigned char)((data >> 58) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(7 + j * 8), south, (unsigned char)((data >> 60) & 0x03));
      g_map.wallDataSet((unsigned char)n, (unsigned char)(7 + j * 8), west, (unsigned char)((data >> 62) & 0x03));

      m = m + 8;
    }
  }
}

void flashErase(int page) {
  uint32_t error_sector;

  HAL_FLASH_Unlock();

  FLASH_EraseInitTypeDef EraseInitStruct;
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;  //Mass erase or page erase. FLASH_TYPEERASE_PAGES or FLASH_TYPEERASE_MASSERASE
  EraseInitStruct.Banks = FLASH_BANK_1;               //FLASH_BANK_BOTH should be used only for mass erase
  EraseInitStruct.Page = page;                        //イレースを開始するページ番号
  EraseInitStruct.NbPages = 1;                        //イレースするページ数

  // Eraseに失敗したページ番号がerror_sectorに入る
  // 正常にEraseができたときは0xFFFFFFFFが入る
  HAL_FLASHEx_Erase(&EraseInitStruct, &error_sector);

  HAL_FLASH_Lock();
}

void flashPalamWrite(uint32_t add, uint64_t data) {
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, add, data);
}

uint64_t flashPalamRead(uint32_t add) {
  return *(uint64_t *)add;
}
