/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The LiteralTable is used to store/retrive
 * literals that have been defined in the
 * source code.
 ******************************************/
#ifndef LITERALTABLE_H
#define LITERALTABLE_H

#include <map>
#include <string>
#include <vector>
#include "Literal.h"

typedef std::map<std::string, Literal> literal_map;
typedef std::pair<std::string, Literal> literal_pair;

class LiteralTable
{
	public:
		/**
		 * Constructor for the LiteralTable;
		 */
		LiteralTable();
		/**
		 * Returns an Literal based on the
		 * literal string provided.
		 * @param literalString The string to lookup.
		 * @return The literal data that is being
		 *  searched for.
		 */
		static Literal Get(std::string literalString);

		static Literal* GetPointer(std::string literalString);

		static std::vector<Literal> GetUnpooled();

		/**
		 * Checks if the literal is in the table.
		 * @param literalString The literal to lookup.
		 * @return true if the literal is in the table,
		 * otherwise false.
		 */
		static bool IsLiteralInTable(std::string literalString);
		/**
		 * Inserts a new literal into the table.
		 * @param literal The literal to insert.
		 */
		static void Insert(Literal literal);
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
		static literal_map _literalTable;

};

#endif

