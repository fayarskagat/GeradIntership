#include <ilcplex/ilocplex.h>
ILOSTLBEGIN

static void populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c);

int main (void) {
  IloEnv env;
  try {

      IloModel model(env); // declaration du nodel
      IloNumVarArray var(env); // liste des variables de decision
      IloRangeArray con(env); // liste des contraintes a ajouter a notre probleme
      IloNumVarArray duals(env);

      populatebyrow (model, var, con); // remplir les variables avec les valeurs adequat
      IloCplex cplex(model);
      cplex.solve();

      env.out() << "Solution status = " << cplex.getStatus() << endl;
      env.out() << "Solution value  = " << cplex.getObjValue() << endl;
      IloNumArray vals(env);
      cplex.getValues(vals, var);
      env.out() << "Values = " << vals << endl;
      cplex.getSlacks(vals, con);
      env.out() << "Slacks = " << vals << endl;
      


      model.add(var[0] == 0);
      cplex.solve();
      cplex.getValues(vals, var);
      env.out() << "Solution status = " << cplex.getStatus() << endl;
      env.out() << "Solution value  = " << cplex.getObjValue() << endl;
      env.out() << "Values = " << vals << endl;
      env.out() << "Ray = " << cplex.getRay() << endl;

      //cplex.exportModel("pl.lp");
    }
    catch (IloException& e) {
      cerr << "Concert exception caught: " << e << endl;
    }
    catch (...) {
      cerr << "Unknown exception caught" << endl;
    }
  env.end();
  return 0;
}

static void populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c) {
  
  IloEnv env = model.getEnv();
  IloNumArray costs(env);
  IloNumArray time(env);

  int costs_array[]  = {1,1,1,10,1,12,2,2,5,10};
  int time_array[]  = {10,1,7,3,2,3,2,3,7,1};
  

  for(int i=0;i<10;i++)
    costs.add(costs_array[i]);

  for(int i=0;i<10;i++)
    time.add(time_array[i]);

  x.add(IloBoolVar(env,"x12")); //0
  x.add(IloBoolVar(env,"x24")); //1
  x.add(IloBoolVar(env,"x46")); //2
  x.add(IloBoolVar(env,"x13")); //3
  x.add(IloBoolVar(env,"x32")); //4
  x.add(IloBoolVar(env,"x35")); //5
  x.add(IloBoolVar(env,"x56")); //6
  x.add(IloBoolVar(env,"x25")); //7
  x.add(IloBoolVar(env,"x34")); //8
  x.add(IloBoolVar(env,"x45")); //9
  
  model.add(IloMinimize(env, costs[0]*x[0] + costs[1]*x[1] + costs[2]*x[2] + costs[3]*x[3] + costs[4]*x[4] + costs[5]*x[5] + costs[6]*x[6] + costs[7]*x[7] + costs[8]*x[8] + costs[9]*x[9]));
  c.add(x[0]+ x[3] == 1); // arcs sortant du noeud de depart
  c.add(x[2]+ x[6] == 1); // arcs entrant au noeud d arrivee
  c.add(x[1]+ x[7] - x[0] - x[4] == 0);
  c.add(x[8]+ x[5] - x[3] == 0);
  c.add(x[9]+ x[2] - x[1] - x[8] == 0);
  c.add(x[6]- x[7] - x[5] - x[9] == 0);
  c.add(time[0]*x[0] + time[1]*x[1] + time[2]*x[2] + time[3]*x[3] + time[4]*x[4] + time[5]*x[5] + time[6]*x[6] + time[7]*x[7] + time[8]*x[8] + time[9]*x[9] <= 14);

  model.add(c);
}



