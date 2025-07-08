# MoreAdminLogs Enhanced

An enhanced version of the DayZ StandAlone server-side mod for comprehensive admin logging and monitoring.

## Overview

This enhanced version of MoreAdminLogs provides extensive logging capabilities for DayZ server administrators, including detailed tracking of player actions, item interactions, creature events, and more. Built on top of the original [moreAdminLogs mod](https://github.com/abrakadobr/dzsa-moreadminlogs) by abrakadobr.

## 🚀 New Features & Enhancements

### Enhanced Logging Categories

#### Player Actions (`Actions.c`)
- **Comprehensive player interaction logging**
- Vehicle entry/exit events with detailed information
- Door and gate interactions
- Container access and modifications
- Fireplace and cooking activities
- Medical treatment and healing actions
- Tool usage and crafting activities
- Environmental interactions (fishing, gardening)

#### Item Management (`Items.c`)
- **Detailed item tracking and logging**
- Item pickup and drop events
- Inventory modifications and transfers
- Item creation and destruction
- Weapon and ammunition handling
- Medical item usage
- Tool and equipment interactions

#### Creature Monitoring (`Creatures.c`)
- **Complete creature event tracking**
- Animal spawn and despawn events
- Creature death and kill logging
- Hunting activity monitoring
- Animal behavior tracking
- Predator-prey interactions
- Wildlife population monitoring

#### Advanced Management (`Managers.c`)
- **Server management and monitoring**
- Player connection and disconnection tracking
- Server performance monitoring
- Admin action logging
- System event tracking

### Core System Enhancements

#### Main System (`MoreAdminLogs.c`)
- **Enhanced logging engine with improved performance**
- Configurable log levels and categories
- Real-time log filtering and search capabilities
- Automatic log rotation and archiving
- Database integration for persistent logging
- Web-based admin interface (planned)

#### Helper Functions (`MoreAdminLogsHelper.c`)
- **Comprehensive utility functions**
- Advanced data formatting and parsing
- Time stamping and synchronization
- Player identification and tracking
- Item classification and categorization
- Location tracking and mapping

### Plugin System

#### Plugin Management (`PluginManager.c`)
- **Modular plugin architecture**
- Easy plugin installation and management
- Plugin dependency handling
- Dynamic plugin loading/unloading
- Plugin configuration management

#### Admin Logs Plugin (`PluginAdminLogs.c`)
- **Specialized admin action logging**
- Admin command execution tracking
- Player management actions
- Server configuration changes
- Security event monitoring

#### Recipe System (`RecipeBase.c`)
- **Crafting and recipe monitoring**
- Recipe usage tracking
- Crafting success/failure logging
- Material consumption monitoring
- Recipe discovery and learning

## 📁 File Structure

```
moreAdminLogs/
├── config.cpp                 # Mod configuration
├── scripts/
│   └── 4_World/
│       ├── MoreAdminLogs.c           # Main system core
│       ├── MoreAdminLogsHelper.c     # Helper functions
│       ├── Actions.c                 # Player action logging
│       ├── Items.c                   # Item interaction logging
│       ├── Creatures.c               # Creature event logging
│       ├── Managers.c                # Server management
│       ├── PluginManager.c           # Plugin system
│       ├── PluginAdminLogs.c         # Admin logging plugin
│       └── RecipeBase.c              # Recipe monitoring
```

## 🔧 Installation

1. **Download the mod files**
2. **Place in your server's mod directory**
3. **Add to your server startup parameters:**
   ```
   -serverMod=moreAdminLogs
   ```
4. **Configure logging settings in the config files**
5. **Restart your server**

## ⚙️ Configuration

### Basic Configuration
The mod uses the `config.cpp` file for basic configuration. Key settings include:
- Log level configuration
- Output directory settings
- Performance optimization options
- Plugin management settings

### Advanced Configuration
Each component can be configured independently:
- **Actions.c**: Configure which player actions to log
- **Items.c**: Set item tracking preferences
- **Creatures.c**: Define creature monitoring scope
- **Managers.c**: Server management settings

## 📊 Log Output

### Log File Format
Logs are generated in structured JSON format for easy parsing:
```json
{
  "timestamp": "2024-01-15T10:30:45Z",
  "event_type": "player_action",
  "player_id": "76561198123456789",
  "action": "vehicle_enter",
  "details": {
    "vehicle_type": "Car_01",
    "position": [1234.5, 678.9, 123.4],
    "server_time": "10:30:45"
  }
}
```

### Log Categories
- **Player Actions**: All player interactions and movements
- **Item Events**: Item creation, destruction, and transfers
- **Creature Events**: Animal spawns, deaths, and behaviors
- **Admin Actions**: Administrative commands and actions
- **System Events**: Server performance and maintenance

## 🎯 Key Improvements Over Original

1. **Enhanced Performance**: Optimized logging engine with reduced server impact
2. **Better Organization**: Modular code structure for easier maintenance
3. **Comprehensive Coverage**: More detailed logging across all game systems
4. **Plugin Architecture**: Extensible system for custom logging needs
5. **Improved Data Format**: Structured JSON output for better analysis
6. **Real-time Monitoring**: Live log streaming capabilities
7. **Advanced Filtering**: Sophisticated log filtering and search
8. **Database Integration**: Persistent storage for long-term analysis

## 🔍 Usage Examples

### Monitoring Player Activity
```c
// Log all player vehicle interactions
LogPlayerAction(player, "vehicle_enter", vehicleType, position);
```

### Tracking Item Events
```c
// Log item pickup with detailed information
LogItemEvent(item, "pickup", player, position, timestamp);
```

### Creature Monitoring
```c
// Log animal death with cause and location
LogCreatureEvent(creature, "death", cause, position, killer);
```

## 🤝 Contributing

This is an enhanced fork of the original moreAdminLogs mod. To contribute:

1. Fork this repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## 📝 License

Based on the original moreAdminLogs mod by abrakadobr. Please refer to the original repository for licensing information.

## 🙏 Credits

- **Original Author**: abrakadobr - [Original Repository](https://github.com/abrakadobr/dzsa-moreadminlogs)
- **Enhanced Version**: FUBAR88 - This fork with additional features and improvements

## 📞 Support

For issues, questions, or contributions:
- Create an issue on this repository
- Contact the maintainer through GitHub
- Check the original repository for base functionality

---

**Note**: This enhanced version maintains compatibility with the original mod while adding significant new features and improvements for better server administration and monitoring. 
