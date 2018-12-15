#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>


typedef std::map<std::string, int> register_map;
typedef std::pair<std::string, int> register_pair;

/**
 * The register class represents all the data
 * stored in each of the registers.
 */
class Registers
{
	public:
		/**
		 * Looks up the data in resiters based on string of the register
		 * passed in.
		 * @param register The register
		 */
		int Get(std::string reg);
		/**
		 * Inserts data into the register.
		 * @param register The register to insert the memory.
		 * @param data The data to insert.
		 */
		void Insert(std::string reg, int data);

		/**
		 * A 0 Accumulator
		 */
		static const std::string A;
		/**
		 * X 1 Index register
		 */
		static const std::string X;
		/**
		 * L 2 Linkage register (JSUB/RSUB)
		 */
		static const std::string L;
		/**
		 * B (SIC/XE) 3 Base register
		 */
		static const std::string B;
		/**
		 * S (SIC/XE) 4 General register
		 */
		static const std::string S;
		/**
		 * T (SIC/XE) 5 General register
		 */
		static const std::string T;
		/**
		 * F (SIC/XE) 6 Floating Point
		 * Accumulator (48 bits)
		 */
		static const std::string F;
		/**
		 * PC 8 Program Counter (PC)
		 */
		static const std::string PC;
		/**
		 * SW 9 Status Word (includes Condition Code, CC)
		 */
		static const std::string SW;

	private:
		/**
		 * The map of register data.
		 */
		register_map _registers;

};


#endif
