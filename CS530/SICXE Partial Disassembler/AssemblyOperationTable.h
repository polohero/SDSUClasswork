#ifndef ASSEMBLYOPERATIONTABLE_H
#define ASSEMBLYOPERATIONTABLE_H

#include <map>
#include "AssemblyOperation.h"

typedef std::map<int, AssemblyOperation> assembly_map;
typedef std::pair<int, AssemblyOperation> assembly_pair;

/**
 * The AssemblyOperationTable is an object that
 * contains a mapping between an op code and
 * an AssemblyOperation. Use this class to lookup
 * all the details of an AssemblyOperation by the op code.
 */
class AssemblyOperationTable
{
	public:
		/**
		 * Constructor for the AssemblyOperationTable;
		 */
		AssemblyOperationTable();
		/**
		 * Returns an AssemblyOperation based on the
		 * opCode provided..
		 * @param opCode The op code to lookup.
		 * @return The operation data that is being
		 *  searched for.
		 */
		AssemblyOperation Get(int opCode);
		/**
		 * Checks if the op code is in the table.
		 * @param opCode The op code to lookup.
		 * @return true if the operation is in the table,
		 * otherwise false.
		 */
		bool IsValidOpcode(int opCode);

	private:

		// Keeping these all as static to save memory.
		// There is no need to load a whole new table
		// for all instances since the data is the same.

		/**
		 * Inserts an assembly operation into the map.
		 * @param operation The operation to insert.
		 */
		static void insert(AssemblyOperation operation);
		/**
		 * Fills the table up with all of the data.
		 */
		static void load();
		/**
		 * The table that holds all of the operations.
		 */
		static assembly_map _operationTable;
		/**
		 * We only need to load the table once,
		 * this will keep track if it's been loaded.
		 */
		static bool _loaded;

};

#endif

