var mongoose = require('mongoose')

var cryptoSchema = new mongoose.Schema({
    symbol: {
        type: String,
        required: true,
        maxLength: 10,
        trim: true,
        unique: true
    },
    name: {
        type: String,
        required: true,
        maxLength: 32,
        trim: true,
        unique: true
    },
    logo: {
        data: Buffer,
        contentType: String
    },
    crypto_type: {
        type: Number,
        required: true,
        default: 0
    }
},
    { timestamps: true }
);

module.exports = mongoose.model("Crypto", cryptoSchema);