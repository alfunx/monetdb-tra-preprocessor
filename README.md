# monetdb-tra-preprocessor

A super awesome distributed database system, that implements the distributed
track-join.


## Build

To prepare the build environment, run the following commands once:

```bash
cd build
cmake ..
```

To build the project, run:

```bash
cd build
make
```


## Usage

The preprocessor takes an SQL query as argument:

```bash
cd build
# ./monetdb-tra-preprocessor [sql-query]
./monetdb-tra-preprocessor 'SELECT * FROM TRA (r ON a, b ORDER BY id);'
```

It produces the schema specification for the transpose operator (TRA) by
evaluating the input relation (here `r`).


## MonetDB Integration

To be able to use the preprocessor from within MonetDB, place the executable
file `monetdb-tra-preprocessor` in a directory in `$PATH`.
