/*---------------------------------------------------------------------------*\
License
    AeroSolved
    Copyright (C) 2017 Philip Morris International

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
\*---------------------------------------------------------------------------*/

#include "driftVelocityModel.H"

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace Foam
{
    defineTypeNameAndDebug(driftVelocityModel, 0);
    defineRunTimeSelectionTable(driftVelocityModel, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::driftVelocityModel::driftVelocityModel
(
    const fvMesh& mesh,
    aerosolModel& aerosol
)
:
    IOdictionary
    (
        IOobject
        (
            "driftVelocityProperties",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    ),
    mesh_(mesh),
    aerosol_(aerosol),
    thermo_(aerosol.thermo()),
    params_(subDict("driftVelocityModelParameters"))
{
    // Set the aerosol model function pointers to getDriftVel()

    aerosol.updateDropDriftVelFields = boost::bind(&driftVelocityModel::updateDropDriftVelFields, this);
    aerosol.updateDropDriftVelField = boost::bind(&driftVelocityModel::updateDropDriftVelField, this, _1);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::driftVelocityModel::~driftVelocityModel()
{
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::driftVelocityModel::read()
{
    if (regIOobject::read())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// ************************************************************************* //
