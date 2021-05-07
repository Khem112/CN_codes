var mongoose = require("mongoose");

var couponSchema = new mongoose.Schema({
    couponCode: {
        type: String,
        required: true,
        unique: true,
        trim: true
    },
    discountPercent: {
        type: Number,
        required: true,
    },
    discountMaxLimit: {
        type: Number,
    },
    contentType: {
        type: Number,
        /*
            (0-all,1-weekly,2-daily,contest_id-for that contest)
        */
        required: true,
    },
    userType: {
        type: Number,
        /*
            (0-all,1-admins,usr_id-for that user only)
        */
        required: true
    }
});

module.exports = mongoose.model("Coupon", couponSchema);

