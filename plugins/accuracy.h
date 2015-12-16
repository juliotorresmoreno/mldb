/** accuracy.h                                                   -*- C++ -*-
    Jeremy Barnes, 22 January 2015
    Copyright (c) 2015 Datacratic Inc.  All rights reserved.

    This file is part of MLDB. Copyright 2015 Datacratic. All rights reserved.

    Accuracy procedure and functions.
*/

#pragma once

#include "mldb/core/dataset.h"
#include "mldb/core/procedure.h"
#include "mldb/core/function.h"
#include "matrix.h"
#include "mldb/types/value_description.h"
#include "mldb/types/optional.h"

namespace Datacratic {
namespace MLDB {


class SqlExpression;


struct AccuracyConfig : public ProcedureConfig {
    AccuracyConfig()
        :  weight(SqlExpression::ONE)
    {
    }

    /// Sql query to select the testing data
    InputQuery testingData;

    /// Dataset we output to
    Optional<PolyConfigT<Dataset> > outputDataset;
    static constexpr char const * defaultOutputDatasetType = "sparse.mutable";

    /// The expression to generate the score, normally the name of the score value
    std::shared_ptr<SqlExpression> score;

    /// The expression to generate the weight
    std::shared_ptr<SqlExpression> weight;
};

DECLARE_STRUCTURE_DESCRIPTION(AccuracyConfig);


/*****************************************************************************/
/* ACCURACY PROCEDURE                                                         */
/*****************************************************************************/

/** Procedure that calculates the accuracy of a classifier. */

struct AccuracyProcedure: public Procedure {

    AccuracyProcedure(MldbServer * owner,
                     PolyConfig config,
                     const std::function<bool (const Json::Value &)> & onProgress);
    
    virtual RunOutput run(const ProcedureRunConfig & run,
                          const std::function<bool (const Json::Value &)> & onProgress) const;
    
    virtual Any getStatus() const;
    
    AccuracyConfig accuracyConfig;
};


} // namespace MLDB
} // namespace Datacratic
