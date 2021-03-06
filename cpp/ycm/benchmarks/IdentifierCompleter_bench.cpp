// Copyright (C) 2017 ycmd contributors
//
// This file is part of ycmd.
//
// ycmd is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ycmd is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ycmd.  If not, see <http://www.gnu.org/licenses/>.

#include "benchmark/benchmark_api.h"
#include "BenchUtils.h"
#include "CandidateRepository.h"
#include "IdentifierCompleter.h"

namespace YouCompleteMe {

class IdentifierCompleterFixture : public benchmark::Fixture {
public:
  void SetUp( const benchmark::State& ) {
    CandidateRepository::Instance().ClearCandidates();
  }
};


BENCHMARK_DEFINE_F( IdentifierCompleterFixture, CandidatesWithCommonPrefix )(
    benchmark::State& state ) {

  std::vector< std::string > candidates;
  candidates = GenerateCandidatesWithCommonPrefix( "a_A_a_",
                                                   state.range( 0 ) );
  IdentifierCompleter completer( candidates );

  while ( state.KeepRunning() )
    completer.CandidatesForQuery( "aA" );

  state.SetComplexityN( state.range( 0 ) );
}


BENCHMARK_REGISTER_F( IdentifierCompleterFixture, CandidatesWithCommonPrefix )
    ->RangeMultiplier( 2 )
    ->Range( 1, 1 << 16 )
    ->Complexity();

} // namespace YouCompleteMe
