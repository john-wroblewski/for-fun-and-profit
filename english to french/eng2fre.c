#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* the trie node data structure */
typedef struct s_trie_node
{
	char * translation; /* NULL if node not a word */

	/* pointer array to child nodes */
	struct s_trie_node * children[UCHAR_MAX+1];
} * p_trie_node;

/* pointer to the root node of the trie structure */
static p_trie_node proot = NULL;

/* helper functions for trie structure */

/* allocate new node on the heap
   output: pointer to new node (must be freed) */
struct s_trie_node * new_node(void);

/* delete node and all its children
   input: pointer to node to delete
   postcondition: node and children are freed */
void delete_node(struct s_trie_node * pnode);

/* add word to trie, with translation
   input: word and translation
   output: non-zero if new node added, zero otherwise
   postcondition: word exists in trie */
int add_word(const char * word, char * translation);

/* read dictionary file into trie structure */
unsigned int load_dictionary(const char * filename);

/* search trie structure for word and return translations
   input: word to search
   output: translation, or NULL if not found */
char * lookup_word(const char * word);

/* maximum number of characters for word to search */
#define WORD_MAX 256

/* maximum number of characters in line */
#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

int main(int argc, char * argv[]) {
	char word[WORD_MAX], * translation;
	int len;

	if (argc <= 1)
		return 0; /* no dictionary specified */

	/* load dictionary */
	proot = new_node();
	load_dictionary(argv[1]);

	do {
		printf("Enter word to translate: ");
		fflush(stdout);
		if (!fgets(word, WORD_MAX, stdin))
			abort();

		/* strip trailing newline */
		len = strlen(word);
		if (len > 0 && word[len-1] == '\n') {
			word[len-1] = '\0';
			--len;
		}

		/* exit on empty string */
		if (len == 0)
			break;

		/* lookup word */
		translation = lookup_word(word);

		if (translation)
			printf("%s -> %s\n", word, translation);
		else
			printf("\"%s\" not found\n", word);
	} while (1);

	/* clean up trie structure */
	delete_node(proot);

	return 0;
}

/* allocate new node on the heap
   output: pointer to new node (must be freed) */
p_trie_node new_node(void) {
	int i;
	p_trie_node pnode = malloc( sizeof( struct s_trie_node ) );
	if( pnode ) {
		pnode->translation = NULL;
		for( i = 0; i < ( UCHAR_MAX + 1 ); i++ )
			pnode->children[ i ] = NULL;
	}
	return pnode;
}

/* delete node and all its children
   input: pointer to node to delete
   postcondition: node and children are freed */
void delete_node(p_trie_node pnode) {
	p_trie_node psubnode;
	unsigned int i;
	if( pnode->translation )
		free( pnode->translation );
	for( i = 0 ; i < UCHAR_MAX + 1; i++ ) {
		if( ( psubnode = pnode->children[ i ] ) )
			delete_node( psubnode );
	}
	free( pnode );
}

/* add word to trie, with translation
   input: word and translation
   output: non-zero if new node added, zero otherwise
   postcondition: word exists in trie */
int add_word(const char * word, char * translation) {
	unsigned int i , oldlen , newlen;
	p_trie_node pnode = proot;
	char * pc;
	/* locating word in trie: create word if not there */
	for( i = 0; word[ i ] != '\0'; i++ ){
		if( !( ( unsigned int )word[ i ] && ( ( unsigned int )word[ i ] <= UCHAR_MAX + 1 ) ) )
			return 0;
		if( !( pnode->children[ ( unsigned int )( word[ i ] ) ] ) )
			pnode->children[ ( unsigned int )( word[ i ] ) ] = new_node();
		if( !( pnode = pnode->children[ ( unsigned int )( word[ i ] ) ] ) )
			return 0;
	}
	oldlen = ( pnode->translation ) ? strlen( pnode->translation ) : 0;
	newlen = strlen( translation ) + ( ( oldlen ) ? ( oldlen + 2 ) : 1 );
	/* append new translation */
	if( oldlen ) {
                if( !( pc = malloc( newlen ) ) )
                        return 1;
                strcpy( pc , pnode->translation );
                pc[ oldlen ] = ',';
                free( pnode->translation );
                strcpy( ( ( pnode->translation = pc ) + ( oldlen + 1 ) ) , translation );
                return 2;
        }
        /* copy translation into null pointer */
        if( !( pnode->translation = malloc( newlen ) ) )
                return 0;
        strcpy( pnode->translation , translation );
	return 3;
}

/* delimiter for dictionary */
#define DELIMS "\t"

/* read dictionary file into trie structure */
unsigned int load_dictionary(const char * filename) {
	FILE * pfile;
	char line[LINE_MAX], * word, * translation;
	unsigned int icount = 0;

	/* ensure file can be opened */
	if ( !(pfile = fopen(filename,"r")) )
		return icount;

	/* read lines */
	while ( (fgets(line, LINE_MAX, pfile)) ) {
		/* strip trailing newline */
		int len = strlen(line);
		if (len > 0 && line[len-1] == '\n') {
			line[len-1] = '\0';
			--len;
		}

		if (len == 0 || line[0] == '#')
			continue; /* ignore comment/empty lines */

		/* separate word and translation */
		word = line + strspn(line, DELIMS);
		if ( !word[0] )
			continue; /* no word in line */
		translation = word + strcspn(word, DELIMS);
		*translation++ = '\0';
		translation += strspn(translation, DELIMS);

		/* add word to trie */
		if (add_word(word, translation))
			icount++;
	}
	fclose(pfile);
	return icount;
}

/* search trie structure for word and return translations
   input: word to search
   output: translation, or NULL if not found */
char * lookup_word(const char * word) {
	unsigned int i;
	p_trie_node pnode = proot;

	for( i = 0; word[ i ] != '\0'; i++ )
		if( !( pnode = pnode->children[ ( unsigned int )( word[ i ] ) ] ) )
			return NULL;
	return pnode->translation;
}

