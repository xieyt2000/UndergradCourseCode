package submit;

// some useful things to import. add any additional imports you need.

import joeq.Compiler.Quad.*;
import flow.Flow;
import joeq.Main.Helper;

import java.util.Set;
import java.util.TreeSet;

/**
 * Skeleton class for implementing a faint variable analysis
 * using the Flow.Analysis interface.
 */
public class Faintness implements Flow.Analysis {

    /**
     * Class for the dataflow objects in the Faintness analysis.
     * You are free to change this class or move it to another file.
     */
    public static class NotFaintVarSet implements Flow.DataflowObject {
        /**
         * Methods from the Flow.DataflowObject interface.
         * See Flow.java for the meaning of these methods.
         * These need to be filled in.
         */
        private Set<String> set = new TreeSet<>();
        private static Set<String> universalSet;
        ;

        public void setToTop() {
        }

        public void setToBottom() {
        }

        public void meetWith(Flow.DataflowObject o) {
            set.addAll(((NotFaintVarSet) o).set);
        }

        public void copy(Flow.DataflowObject o) {
            set = new TreeSet<>(((NotFaintVarSet) o).set);
        }

        public NotFaintVarSet getCopy() {
            NotFaintVarSet ret = new NotFaintVarSet();
            ret.copy(this);
            return ret;
        }

        /**
         * toString() method for the dataflow objects which is used
         * by postprocess() below.  The format of this method must
         * be of the form "[REG0, REG1, REG2, ...]", where each REG is
         * the identifier of a register, and the list of REGs must be sorted.
         * See src/test/TestFaintness.out for example output of the analysis.
         * The output format of your reaching definitions analysis must
         * match this exactly.
         * since `set` is the set of not faint vars, output the complement set
         */
        @Override
        public String toString() {
            TreeSet<String> res = new TreeSet<>(universalSet);
            res.removeAll(set);
            return res.toString();
        }

        @Override
        public boolean equals(Object o) {
            if (o instanceof NotFaintVarSet) {
                NotFaintVarSet a = (NotFaintVarSet) o;
                return set.equals(a.set);
            }
            return false;
        }

        @Override
        public int hashCode() {
            return set.hashCode();
        }

        public void killVar(String v) {
            set.remove(v);
        }
    }

    /**
     * Dataflow objects for the interior and entry/exit points
     * of the CFG. in[ID] and out[ID] store the entry and exit
     * state for the input and output of the quad with identifier ID.
     * <p>
     * You are free to modify these fields, just make sure to
     * preserve the data printed by postprocess(), which relies on these.
     */
    private NotFaintVarSet[] in, out;
    private NotFaintVarSet entry, exit;

    /**
     * This method initializes the datflow framework.
     *
     * @param cfg The control flow graph we are going to process.
     */
    public void preprocess(ControlFlowGraph cfg) {
        // this line must come first.
        System.out.println("Method: " + cfg.getMethod().getName().toString());

        // get the amount of space we need to allocate for the in/out arrays.
        QuadIterator qit = new QuadIterator(cfg);
        int max = 0;
        while (qit.hasNext()) {
            int id = qit.next().getID();
            if (id > max)
                max = id;
        }
        max += 1;

        // allocate the in and out arrays.
        in = new NotFaintVarSet[max];
        out = new NotFaintVarSet[max];

        // initialize the contents of in and out.
        qit = new QuadIterator(cfg);
        while (qit.hasNext()) {
            int id = qit.next().getID();
            in[id] = new NotFaintVarSet();
            out[id] = new NotFaintVarSet();
        }

        // initialize the entry and exit points.
        entry = new NotFaintVarSet();
        exit = new NotFaintVarSet();

        /************************************************
         * Your remaining initialization code goes here *
         ************************************************/
        // initialize universalSet
        Set<String> s = new TreeSet<String>();
        NotFaintVarSet.universalSet = s;

        /* Arguments are always there. */
        int numargs = cfg.getMethod().getParamTypes().length;
        for (int i = 0; i < numargs; i++) {
            s.add("R" + i);
        }

        qit = new QuadIterator(cfg);
        while (qit.hasNext()) {
            Quad q = qit.next();
            for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
                s.add(def.getRegister().toString());
            }
            for (Operand.RegisterOperand use : q.getUsedRegisters()) {
                s.add(use.getRegister().toString());
            }
        }

        transferfn.val = new NotFaintVarSet();
        System.out.println("Initialization completed.");
    }

    /**
     * This method is called after the fixpoint is reached.
     * It must print out the dataflow objects associated with
     * the entry, exit, and all interior points of the CFG.
     * Unless you modify in, out, entry, or exit you shouldn't
     * need to change this method.
     *
     * @param cfg Unused.
     */
    public void postprocess(ControlFlowGraph cfg) {
        System.out.println("entry: " + entry.toString());
        for (int i = 1; i < in.length; i++) {
            if (in[i] != null) {
                System.out.println(i + " in:  " + in[i].toString());
                System.out.println(i + " out: " + out[i].toString());
            }
        }
        System.out.println("exit: " + exit.toString());
    }

    /**
     * Other methods from the Flow.Analysis interface.
     * See Flow.java for the meaning of these methods.
     * These need to be filled in.
     */
    public boolean isForward() {
        return false;
    }

    public Flow.DataflowObject getEntry() {
        return entry.getCopy();
    }

    public Flow.DataflowObject getExit() {
        return exit.getCopy();
    }

    public void setEntry(Flow.DataflowObject value) {
        entry.copy(value);
    }

    public void setExit(Flow.DataflowObject value) {
        exit.copy(value);
    }

    public Flow.DataflowObject getIn(Quad q) {
        return in[q.getID()].getCopy();
    }

    public Flow.DataflowObject getOut(Quad q) {
        return out[q.getID()].getCopy();
    }

    public void setIn(Quad q, Flow.DataflowObject value) {
        in[q.getID()].copy(value);
    }

    public void setOut(Quad q, Flow.DataflowObject value) {
        out[q.getID()].copy(value);
    }

    public Flow.DataflowObject newTempVar() {
        return new NotFaintVarSet();
    }

    private TransferFunction transferfn = new TransferFunction();

    public void processQuad(Quad q) {
        transferfn.val.copy(out[q.getID()]);
        transferfn.addVal = (NotFaintVarSet) newTempVar();
        Helper.runPass(q, transferfn);
        in[q.getID()].copy(transferfn.val);
    }

    /* The QuadVisitor that actually does the computation */
    public static class TransferFunction extends QuadVisitor.EmptyVisitor {
        NotFaintVarSet val;
        NotFaintVarSet addVal;

        private void addUsed(Quad q) {
            for (Operand.RegisterOperand use : q.getUsedRegisters()) {
                addVal.set.add(use.getRegister().toString());
            }
        }

        private void killDef(Quad q) {
            for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
                val.killVar(def.getRegister().toString());
            }
        }

        @Override
        public void visitMove(Quad q) {
            String dst = Operator.Move.getDest(q).getRegister().toString();
            if (val.set.contains(dst)) {
                addUsed(q);
            }
        }

        @Override
        public void visitBinary(Quad q) {
            String dst = Operator.Binary.getDest(q).getRegister().toString();
            if (val.set.contains(dst)) {
                addUsed(q);
            }
        }

        @Override
        public void visitQuad(Quad q) {
            killDef(q);
            Operator operator = q.getOperator();
            if (!((operator instanceof Operator.Move) || (operator instanceof Operator.Binary))) {
                addUsed(q);
            }
            val.set.addAll(addVal.set);
        }
    }
}
