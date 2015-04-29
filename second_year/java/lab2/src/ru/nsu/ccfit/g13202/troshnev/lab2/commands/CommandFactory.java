package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.HashMap;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;
import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;


/**
 * Created by zerlok on 3/25/15.
 */


public class CommandFactory {

    private static final Logger LOG = Logger.getLogger(CommandFactory.class.getName());

    private Context calcContext;
    private HashMap<String, Class<? extends Command> > calcCommands;

    public CommandFactory(Context ctx) {
        calcContext = ctx;
        calcCommands = new HashMap<String, Class<? extends Command> >();
    }

    public void registerCommand (String commandName, Class<? extends Command> commandClass) {
        calcCommands.put(commandName, commandClass);

        LOG.info(String.format("commands.Command %1$s <%2$s> registered.", commandName, commandClass));
    }

    public Command createCommand(String commandName) throws UnknownCommandException {
        LOG.debug(String.format("Start creating %1$s command ...", commandName));
        Command cmd = null;

        try {
            if (calcCommands.containsKey(commandName)) {
                Class commandClass = (Class) calcCommands.get(commandName);
                Constructor commandConstructor = commandClass.getConstructor(new Class[]{calcContext.getClass()});
                cmd = (Command)commandConstructor.newInstance(calcContext);

            } else {
                throw new UnknownCommandException(commandName);
            }

        } catch (NoSuchMethodException e) {
            LOG.fatal(e.getMessage());

        } catch (InvocationTargetException e) {
            LOG.fatal(e.getMessage());

        } catch (InstantiationException e) {
            LOG.fatal(e.getMessage());

        } catch (IllegalAccessException e) {
            LOG.fatal(e.getMessage());
        }

        LOG.debug(String.format("commands.Command %1$s created.", cmd.getClass().getName()));

        return cmd;
    }

    public void configure() throws IOException {
        LOG.info("Start commands registration ...");

        Properties prop = new Properties();
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream("cmd.properties");

        if (inputStream == null) {
            throw new FileNotFoundException("Cannot find cmd.properties file.");
        }
        prop.load(inputStream);
        String cmdFolderPath = prop.getProperty("folder");

        for (String key : prop.stringPropertyNames()) {
            if (!key.contentEquals("folder")) {
                String value = prop.getProperty(key);
                try {
                    calcCommands.put(key, (Class<Command>) Class.forName(cmdFolderPath + "." + value));

                } catch (ClassNotFoundException e) {
                    calcContext.println(new CommandNotFoundException().getMessage());
                }
            }
        }
    }
}
