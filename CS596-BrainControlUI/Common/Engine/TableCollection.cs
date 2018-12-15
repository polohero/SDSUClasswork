using System;
using System.Collections.Concurrent;



namespace Games.Common.Engine
{
    /// <summary>
    /// A collection of tables based on the table id.
    /// </summary>
    public sealed class TableCollection
    {
        public TableCollection()
        {
            _tables = new ConcurrentDictionary<string, Table>();
        }

        /// <summary>
        /// Adds a table or updates the existing info
        /// of the table.
        /// </summary>
        /// <param name="table"></param>
        public void AddOrUpdate(Table table)
        {
            _tables.AddOrUpdate(table.ID, table, (key, oldValue) => table);
        }

        /// <summary>
        /// Gets the table info from the collection.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public Table Get(string id)
        {
            Table table = null;

            _tables.TryGetValue(id, out table);

            return table;
        }

        /// <summary>
        /// Gets the table info from the collection.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public Table Get(Table table)
        {
            Table currentTable = null;

            _tables.TryGetValue(table.ID, out currentTable);

            return currentTable;
        }


        public Table GetOrAdd(Table table)
        {
            return _tables.GetOrAdd(table.ID, table);
        }

        public Table Remove(Table table)
        {
            Table currentTable = null;

            _tables.TryRemove(table.ID, out currentTable);

            return currentTable;
        }

        private ConcurrentDictionary<string, Table> _tables;
    }
}
