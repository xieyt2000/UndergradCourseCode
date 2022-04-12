package submit;

// some useful things to import. add any additional imports you need.

import flow.Liveness;
import joeq.Compiler.Quad.*;
import flow.Flow;

import java.net.Inet4Address;
import java.util.HashMap;
import java.util.TreeSet;

/**
 * Skeleton class for implementing a reaching definition analysis
 * using the Flow.Analysis interface.
 */
public class ReachingDefs implements Flow.Analysis {

    /**
     * Class for the dataflow objects in the ReachingDefs analysis.
     * You are free to change this class or move it to another file.
     */
    public static class DefIDSet implements Flow.DataflowObject {
        private TreeSet<Integer> set = new TreeSet<>();

        /**
         * Methods from the Flow.DataflowObject interface.
         * See Flow.java for the meaning of these methods.
         * These need to be filled in.
         */
        public void setToTop() {
        }

        public void setToBottom() {
        }

        public void meetWith(Flow.DataflowObject o) {
            set.addAll(((DefIDSet) o).set);
        }

        public void copy(Flow.DataflowObject o) {
            set = new TreeSet<>(((DefIDSet) o).set);
        }

        public DefIDSet getCopy() {
            DefIDSet ret = new DefIDSet();
            ret.copy(this);
            return ret;
        }

        /**
         * toString() method for the dataflow objects which is used
         * by postprocess() below.  The format of this method must
         * be of the form "[ID0, ID1, ID2, ...]", where each ID is
         * the identifier of a quad defining some register, and the
         * list of IDs must be sorted.  See src/test/Test.rd.out
         * for example output of the analysis.  The output format of
         * your reaching definitions analysis must match this exactly.
         */
        @Override
        public boolean equals(Object o)
        {
            if (o instanceof DefIDSet)
            {
                DefIDSet a = (DefIDSet) o;
                return set.equals(a.set);
            }
            return false;
        }

        @Override
        public int hashCode() {
            return set.hashCode();
        }

        @Override
        public String toString() {
            return set.toString();
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
    private DefIDSet[] in, out;
    private DefIDSet entry, exit;
    private HashMap<String, TreeSet<Integer>> var2Defs = new HashMap<>();

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
        in = new DefIDSet[max];
        out = new DefIDSet[max];

        // initialize the contents of in and out.
        qit = new QuadIterator(cfg);
        while (qit.hasNext()) {
            int id = qit.next().getID();
            in[id] = new DefIDSet();
            out[id] = new DefIDSet();
        }

        // initialize the entry and exit points.
        entry = new DefIDSet();
        exit = new DefIDSet();

        /************************************************
         * Your remaining initialization code goes here *
         ************************************************/
        for (qit = new QuadIterator(cfg); qit.hasNext(); ) {
            Quad q = qit.next();
            for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
                String var_name = def.getRegister().toString();
                if (!var2Defs.containsKey(var_name)) {
                    var2Defs.put(var_name, new TreeSet<>());
                }
                var2Defs.get(var_name).add(q.getID());
            }
        }
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
        for (int i = 0; i < in.length; i++) {
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
        return true;
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
        return new DefIDSet();
    }

    public void processQuad(Quad q) {
        DefIDSet newOut = (DefIDSet) getIn(q);
        for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
            newOut.set.removeAll(var2Defs.get(def.getRegister().toString()));
        }
        if (!q.getDefinedRegisters().isEmpty()){
            newOut.set.add(q.getID());
        }
        setOut(q, newOut);
    }
}
