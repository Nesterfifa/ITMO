package operators;

import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class Variable implements Expression {
    private final String name;
    protected final Set<Variable> freeVars = new HashSet<>();
    protected final Set<Variable> boundVars = new HashSet<>();
    protected final Set<Variable> usedVars = new HashSet<>();

    public Variable(String name) {
        this.name = name;
        usedVars.add(this);
        freeVars.add(this);
    }

    public String toString() {
        return name;
    }

    @Override
    public String toPrefixString() {
        return name;
    }

    @Override
    public void addBoundVar(Variable variable) {
        boundVars.add(variable);
        freeVars.remove(variable);
    }

    @Override
    public Set<Variable> getFreeVars() {
        return freeVars;
    }

    @Override
    public Set<Variable> getBoundVars() {
        return boundVars;
    }

    @Override
    public Set<Variable> getUsedVars() {
        return usedVars;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Variable variable = (Variable) o;
        return Objects.equals(name, variable.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}
