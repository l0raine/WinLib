#pragma once
#include <stdlib.h>
#include "winstructs.h"
#include "memory.h"
#include "PEFile.h"

namespace WinLib {
	namespace PE {
		namespace Loader {
			class MMapperDriver {
			public:
				enum STATUS {
					SUCCESS,
					FAILED,
					ACCESSDENIED,
					PEINVALID
				};

				MMapperDriver(PEFile *peFile);
				STATUS map();

			private:
				PEFile	*peFile;
				PVOID	mapBase;

				bool mapHeader();
				bool mapSections();
				bool baseRelocation(PVOID targetBase);
				bool fixImports();
				PIMAGE_BASE_RELOCATION processRelocation(ULONG_PTR address, ULONG count, PUSHORT typeOffset, LONGLONG delta);
				bool executeMappedMemory();

				static STATUS mapInternal(MMapperDriver* this_ptr);
			};
		}
	}
}