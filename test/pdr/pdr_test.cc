#include "gtest/gtest.h"

#include "proof/pdr/pdr.h"
#include "proof/pdr/pdrInt.h"
#include "aig/aig/aig.h"

ABC_NAMESPACE_IMPL_START

TEST(PdrTest, InnardsPrioritization) {
  // create a simple AIG with two registers
  Aig_Man_t* pMan = Aig_ManStart(10);
  Aig_Obj_t* pA = Aig_IthVar(pMan, 0);
  Aig_Obj_t* pB = Aig_IthVar(pMan, 1);
  Aig_Obj_t* pAnd = Aig_And(pMan, pA, pB);
  Aig_ObjCreatePo(pMan, pAnd);
  // register count is stored separately
  Aig_ManSetRegNum(pMan, 2);

  Pdr_Par_t Pars;
  Pdr_ManSetDefaultParams(&Pars);
  ASSERT_TRUE(Pars.fNewXSim);

  Pdr_Man_t* pdr = Pdr_ManStart(pMan, &Pars, NULL);
  ASSERT_NE(pdr, nullptr);

  ASSERT_EQ(Vec_IntSize(pdr->vPrio), 2);
  EXPECT_EQ(Vec_IntEntry(pdr->vPrio, 0), 0);
  EXPECT_EQ(Vec_IntEntry(pdr->vPrio, 1), 1);

  Pdr_ManStop(pdr);
  Aig_ManStop(pMan);
}

ABC_NAMESPACE_IMPL_END
