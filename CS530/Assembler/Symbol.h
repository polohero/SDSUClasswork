/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Symbol represents a single symbol
 * that has been written in the source
 * code.
 ******************************************/
#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

class Symbol
{
	public:
		/**
		 * An enum for a register type symbol.
		 */
		static const std::string REGISTER;
		/**
		 * An enum for a labe; type symbol.
		 */
		static const std::string LABEL;
		static const std::string EQU_R;
		static const std::string EQU_A;

		static const std::string REGISTER_A;
		static const int REGISTER_A_ADDRESS;
		static const std::string REGISTER_X;
		static const int REGISTER_X_ADDRESS;
		static const std::string REGISTER_L;
		static const int REGISTER_L_ADDRESS;
		static const std::string REGISTER_B;
		static const int REGISTER_B_ADDRESS;
		static const std::string REGISTER_S;
		static const int REGISTER_S_ADDRESS;
		static const std::string REGISTER_T;
		static const int REGISTER_T_ADDRESS;
		static const std::string REGISTER_F;
		static const int REGISTER_F_ADDRESS;
		static const std::string REGISTER_PC;
		static const int REGISTER_PC_ADDRESS;
		static const std::string REGISTER_SW;
		static const int REGISTER_SW_ADDRESS;

		/**
		 * Constructor for a symbol.
		 * @param label The name of the symbol.
		 * @param address The location of the symbol.
		 * @param symbolType The type of the symbol.
		 */
		Symbol(std::string label, int address, std::string symbolType);
		/*
		 * Returns the name of the symbol.
		 */
		std::string GetLabel();
		/*
		 * Returns the address of the symbol.
		 */
		int GetAddress();
		/*
		 * Returns the type of the symbol.
		 */
		std::string GetSymbolType();

	private:
		int _address;
		std::string _label;
		std::string _symbolType;
};

#endif
