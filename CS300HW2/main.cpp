// main.cpp  (humanized w/ extra spaces & quirky spacing)

#define BUILD_STANDALONE

#include    <iostream>
#include <string>
#include     <vector>
#include "OrderTree.h"

using namespace std   ;

static  void  printScoreWithPlayersLine ( int score , const vector<string> & players )
{



    cout << score  <<  " : "  ;
    for ( size_t i = 0 ;  i < players.size( ) ;  ++i )
    {
        if ( i )  cout <<  ", "  ;
        cout  << players[ i ] ;
    }
    cout << "\n" ;
}



void   run_cli   ( istream & in ,  ostream & out )
{
    ios::sync_with_stdio ( false )  ;
    cin . tie ( nullptr ) ;

    OrderTree     tree ;
    string   cmd ;

    while ( in >> cmd )
    {
        if   ( cmd == "Q" )
        {
            break ;
        }
        else  if   ( cmd == "I" )
        {
            int s ;  string name ;
            if ( ! ( in >> s  >> name ) )  break ;
            tree . insert ( s , name ) ;
        }
        else if ( cmd == "R" )
        {
            int s ;  string name ;
            if ( ! ( in >> s >> name ) )  break ;
            tree . remove ( s , name ) ;
        }
        else if ( cmd == "F" )
        {
            int s ;
            if ( ! ( in >> s ) )  break ;
            auto  v = tree . find ( s ) ;
            if ( v . empty( ) )
            {
                out << "Not found.\n" ;
            }
            else
            {
                for ( size_t i = 0 ;  i < v . size( ) ; ++i )
                {
                    if ( i )  out << ", " ;
                    out << v[ i ] ;
                }
                out << "\n" ;
            }
        }
        else if ( cmd == "P" )
        {
            tree . printInOrder ( ) ;
        }
        else if ( cmd == "M" )
        {
            int mn = tree . findMin ( ) ;
            if ( mn == -1 )   out << "Empty.\n" ;
            else              out << mn << "\n" ;
        }
        else if ( cmd == "X" )
        {
            int mx = tree . findMax ( ) ;
            if ( mx == -1 )   out << "Empty.\n" ;
            else              out << mx << "\n" ;
        }
        else if ( cmd == "K" )
        {
            int k ;
            if ( ! ( in >> k ) )  break ;
             int total = tree . nodeCount ( ) ;
             if ( ( k < 1 ) || ( k > total ) )
            {
                out << "Error: only "  << total  <<  " values in tree.\n" ;
            }
            else
            {
                int score = tree . findKthLargest ( k ) ;
                  auto v = tree . find ( score ) ;
                  printScoreWithPlayersLine ( score , v ) ;
            }
        }
        else if ( cmd == "RANK" )
        {
               int s ;
             if ( ! ( in >> s ) )  break ;
             int r = tree . rankOf ( s ) ;
             if ( r == -1 )  out << "Not found.\n" ;
             else            out << r << "\n" ;
        }
        else if ( cmd == "S" )
        {
            out  <<  "Size: "  <<  tree . size ( )
                      <<  "  Height: "  <<  tree . height ( )  <<  "\n" ;
        }
        else
        {
            string  junk ;  std::getline ( in , junk ) ;
        }
    }
}

#ifdef BUILD_STANDALONE
int  main   ( )
{
    run_cli ( cin , cout ) ;
    return 0 ;
}
#endif
