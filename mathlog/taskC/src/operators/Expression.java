package operators;

import java.util.Set;

public interface Expression {
    String toPrefixString();
    void addBoundVar(Variable variable);
    Set<Variable> getFreeVars();
    Set<Variable> getBoundVars();
    Set<Variable> getUsedVars();
}
