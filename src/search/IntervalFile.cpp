/**
 ** Copyright (c) 2011 Illumina, Inc.
 **
 **
 ** This software is covered by the "Illumina Non-Commercial Use Software
 ** and Source Code License Agreement" and any user of this software or
 ** source file is bound by the terms therein (see accompanying file
 ** Illumina_Non-Commercial_Use_Software_and_Source_Code_License_Agreement.pdf)
 **
 ** This file is part of the BEETL software package.
 **
 ** Citation: Markus J. Bauer, Anthony J. Cox and Giovanna Rosone
 ** Lightweight BWT Construction for Very Large String Collections.
 ** Proceedings of CPM 2011, pp.219-231
 **
 **/

#include "IntervalFile.hh"

#include <cassert>
#include <iostream>

using namespace std;


ostream &operator<<( std::ostream &os, const IntervalRecord &obj )
{
    return os << "{ " << obj.kmer << " interval, position: " << obj.position << ", count: " << obj.count << " }";
}

IntervalWriter::IntervalWriter( std::ostream &file ): file_( file )
{
    assert( file_.good() );
}

void IntervalWriter::write( const IntervalRecord &ir )
{
    file_ << ir.kmer;
    file_ << ' ' << ir.position;
    file_ << ' ' << ir.count << endl;
}

void IntervalWriter::writeV2( const IntervalRecord &ir )
{
    file_ << ir.kmer;
    file_ << ' ' << ir.position;
    file_ << ' ' << ir.count << ':';
    for ( auto pos : ir.dollarSignPositions )
        file_ << ' ' << pos;
    file_ << endl;
}

bool IntervalReader::read( IntervalRecord &ir )
{
    file_ >> ir.kmer;
    file_ >> ir.position;
    file_ >> ir.count;
    if ( file_.good() )
        return true;
    else
        return false;
}

vector<IntervalRecord> IntervalReader::readFullFileAsVector()
{
    vector<IntervalRecord> result;
    IntervalRecord rec;

    while ( read( rec ) )
        result.push_back( rec );

    return result;
}
