// The libMesh Finite Element Library.
// Copyright (C) 2002-2017 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "libmesh/fe_transformation_base.h"
#include "libmesh/h1_fe_transformation.h"
#include "libmesh/hcurl_fe_transformation.h"
#include "libmesh/fe_type.h"

namespace libMesh
{

template<typename OutputShape>
UniquePtr<FETransformationBase<OutputShape>> FETransformationBase<OutputShape>::build( const FEType & fe_type )
{
  switch (fe_type.family)
    {
      // H1 Conforming Elements
    case LAGRANGE:
    case HIERARCHIC:
    case BERNSTEIN:
    case SZABAB:
    case CLOUGH: // PB: Really H2
    case HERMITE: // PB: Really H2
    case SUBDIVISION:
    case LAGRANGE_VEC:
    case MONOMIAL: // PB: Shouldn't this be L2 conforming?
    case XYZ: // PB: Shouldn't this be L2 conforming?
    case L2_HIERARCHIC: // PB: Shouldn't this be L2 conforming?
    case L2_LAGRANGE: // PB: Shouldn't this be L2 conforming?
    case JACOBI_20_00: // PB: For infinite elements...
    case JACOBI_30_00: // PB: For infinite elements...
      return UniquePtr<FETransformationBase<OutputShape>>(new H1FETransformation<OutputShape>);

      // HCurl Conforming Elements
    case NEDELEC_ONE:
      return UniquePtr<FETransformationBase<OutputShape>>(new HCurlFETransformation<OutputShape>);

      // HDiv Conforming Elements
      // L2 Conforming Elements

      // Other...
    case SCALAR:
      // Should never need this for SCALARs
      return UniquePtr<FETransformationBase<OutputShape>>(new H1FETransformation<OutputShape>);

    default:
      libmesh_error_msg("Unknown family = " << fe_type.family);
    }

  libmesh_error_msg("We'll never get here!");
  return UniquePtr<FETransformationBase<OutputShape>>();
}

template class FETransformationBase<Real>;
template class FETransformationBase<RealGradient>;

} // namespace libMesh
