/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SymbolTable is used to store/retrive
 * symbols that have been defined in the
 * source code.
 ******************************************/
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>
#include "Symbol.h"

typedef std::map<std::string, Symbol> symbol_map;
typedef std::pair<std::string, Symbol> symbol_pair;

class SymbolTable
{
	public:
		/**
		 * Constructor for the SymbolTable;
		 */
		SymbolTable();
		/**
		 * Returns an Symbol based on the
		 * label provided..
		 * @param label The op code to lookup.
		 * @return The Symbol data that is being
		 *  searched for.
		 */
		static Symbol* Get(std::string label);
		/**
		 * Checks if the label is in the table.
		 * @param label The label to lookup.
		 * @return true if the label is in the table,
		 * otherwise false.
		 */
		static bool IsSymbolInTable(std::string label);
		/**
		 * Inserts a new symbol into the table.
		 * @param symbol The symbol to insert.
		 */
		static void Insert(Symbol symbol);
		/**
		 * The current size of the table.
		 */
		static int Size();
		/**
		 * Returns a string representation of the
		 * table.
		 */
		static std::string ToString();

	private:
		/**
		 * The table that holds all of the symbols.
		 */
		static symbol_map _symbolTable;

};

#endif

